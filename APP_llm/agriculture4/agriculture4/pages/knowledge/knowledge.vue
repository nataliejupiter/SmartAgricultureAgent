<template>
  <view class="knowledge-page">
    <!-- 顶部操作栏 -->
    <view class="top-bar">
      <view class="filter-row">
        <scroll-view scroll-x class="category-scroll">
          <view
            v-for="cat in categoryList"
            :key="cat"
            class="category-tag"
            :class="{ active: currentCategory === cat }"
            @click="switchCategory(cat)"
          >
            {{ cat }}
          </view>
        </scroll-view>
        <button
          class="compare-toggle"
          :class="{ active: compareMode }"
          @click="toggleCompareMode"
        >
          {{ compareMode ? '退出对比' : '对比' }}
        </button>
      </view>
      <view class="search-box">
        <input
          v-model="searchKeyword"
          placeholder="搜索知识..."
          class="search-input"
        />
      </view>
    </view>

    <!-- 知识列表 -->
    <scroll-view scroll-y class="knowledge-list">
      <view v-if="filteredList.length === 0" class="empty-tip">
        暂无收藏知识，快去主页收藏吧~
      </view>
      <view
        v-for="item in filteredList"
        :key="item.id"
        class="knowledge-card"
        :class="{ selected: selectedIds.includes(item.id) }"
        @click="toggleExpand(item.id)"
        @longpress="toggleSelect(item.id)"
      >
        <view class="card-header">
          <text class="question">{{ item.question }}</text>
          <text class="time">{{ item.time }}</text>
          <!-- 编辑小图标 -->
          <text class="edit-icon" @click.stop="openEdit(item)">✎</text>
        </view>
        <!-- 如果当前卡片被展开，显示完整答案 -->
        <view class="card-answer" v-if="expandedId === item.id">
          {{ item.answer }}
        </view>
        <!-- 未展开时显示摘要 -->
        <view class="card-answer" v-else-if="!compareMode">
          {{ item.answer.slice(0, 80) }}{{ item.answer.length > 80 ? '...' : '' }}
        </view>
        <view class="card-footer">
          <view class="tags">
            <text class="tag" v-for="tag in item.tags" :key="tag">{{ tag }}</text>
          </view>
          <text class="category">{{ item.category }}</text>
        </view>
      </view>
    </scroll-view>

    <!-- 对比弹窗（底部） -->
    <view class="compare-panel" v-if="compareMode && selectedIds.length === 2" @click.stop>
      <view class="compare-title">对比结果</view>
      <scroll-view scroll-y class="compare-content">
        <view class="compare-column" v-for="id in selectedIds" :key="id">
          <view class="compare-item">
            <text class="label">问题：</text>
            <text class="value">{{ getItemById(id).question }}</text>
          </view>
          <view class="compare-item">
            <text class="label">分类：</text>
            <text class="value">{{ getItemById(id).category }}</text>
          </view>
          <view class="compare-item">
            <text class="label">答案：</text>
            <text class="value">{{ getItemById(id).answer }}</text>
          </view>
          <view class="compare-item">
            <text class="label">笔记：</text>
            <text class="value">{{ getItemById(id).notes || '无' }}</text>
          </view>
        </view>
      </scroll-view>
      <button class="close-compare" @click="toggleCompareMode">关闭对比</button>
    </view>

    <!-- 详情/编辑弹窗 -->
    <!-- 自定义编辑弹窗 -->
    <view class="modal-mask" v-if="showDetail" @click="closeDetail"></view>
    <view class="detail-panel" v-if="showDetail && currentItem">
      <view class="detail-question">{{ currentItem.question }}</view>
      <view class="detail-answer">{{ currentItem.answer }}</view>
      <view class="edit-section">
        <text class="edit-label">分类：</text>
        <input v-model="currentItem.category" class="edit-input" placeholder="输入分类" />
      </view>
      <view class="edit-section">
        <text class="edit-label">标签（逗号分隔）：</text>
        <input v-model="tagsInput" class="edit-input" placeholder="例如：种植,病害" />
      </view>
      <view class="edit-section">
        <text class="edit-label">笔记：</text>
        <textarea v-model="currentItem.notes" class="edit-textarea" placeholder="添加你的笔记..." />
      </view>
      <view class="detail-actions">
        <button class="btn-delete" @click="deleteItem(currentItem.id)">删除</button>
        <button class="btn-save" @click="saveItem">保存</button>
      </view>
    </view>
  </view>
</template>

<script setup>
import { ref, computed, onMounted, watch } from 'vue'
import { onShow } from '@dcloudio/uni-app'

// 模拟 ID 生成
const generateId = () => Date.now().toString(36) + Math.random().toString(36).slice(2)

// 所有分类（动态从数据提取，默认加一个“全部”）
const defaultCategories = ['全部', '种植', '养殖', '农机', '政策', '其他']
const categoryList = ref([...defaultCategories])
const currentCategory = ref('全部')
const searchKeyword = ref('')

// 知识数据
const knowledgeList = ref([])

// 对比模式
const compareMode = ref(false)
const selectedIds = ref([])

// 当前编辑的条目
const currentItem = ref(null)
const tagsInput = ref('')

// 当前展开的卡片 id，空字符串表示都不展开
const expandedId = ref('')
const showDetail = ref(false)   // 控制编辑弹窗

const closeDetail = () => {
  showDetail.value = false
}

// 切换展开/收起
const toggleExpand = (id) => {
  if (compareMode.value) {
    toggleSelect(id)
    return
  }
  // 如果点击的是已展开的卡片，则收起；否则展开该卡片
  expandedId.value = expandedId.value === id ? '' : id
}

// 打开编辑弹窗
const openEdit = (item) => {
  currentItem.value = { ...item }
  tagsInput.value = (item.tags || []).join(',')
  showDetail.value = true
}
// ---- 工具函数 ----
const loadData = () => {
  const raw = uni.getStorageSync('knowledge_items') || []
  // 确保每个条目有 tags、category、notes 等字段
  knowledgeList.value = raw.map(item => ({
    ...item,
    id: item.id || generateId(),
    category: item.category || '其他',
    tags: item.tags || [],
    notes: item.notes || ''
  }))
  updateCategoryList()
}

// 更新分类列表（自动合并用户自定义的分类）
const updateCategoryList = () => {
  const cats = new Set(['全部'])
  knowledgeList.value.forEach(item => {
    if (item.category) cats.add(item.category)
  })
  categoryList.value = Array.from(cats)
}

// 保存数据到本地存储
const saveData = () => {
  uni.setStorageSync('knowledge_items', knowledgeList.value)
}

// 切换分类
const switchCategory = (cat) => {
  currentCategory.value = cat
}

// 过滤列表
const filteredList = computed(() => {
  let list = knowledgeList.value
  if (currentCategory.value !== '全部') {
    list = list.filter(item => item.category === currentCategory.value)
  }
  if (searchKeyword.value.trim()) {
    const kw = searchKeyword.value.trim().toLowerCase()
    list = list.filter(item =>
      item.question.toLowerCase().includes(kw) ||
      item.answer.toLowerCase().includes(kw) ||
      item.tags.some(t => t.toLowerCase().includes(kw)) ||
      (item.notes && item.notes.toLowerCase().includes(kw))
    )
  }
  return list
})

// 获取条目
const getItemById = (id) => knowledgeList.value.find(item => item.id === id) || {}

// 打开详情
const openDetail = (item) => {
  if (compareMode) {
    toggleSelect(item.id)
    return
  }
  currentItem.value = { ...item }   // 浅拷贝用于编辑
  tagsInput.value = (item.tags || []).join(',')
  detailPopup.value.open()
}

// 对比模式开关
const toggleCompareMode = () => {
  compareMode.value = !compareMode.value
  selectedIds.value = []
}

// 长按选择/取消对比条目
const toggleSelect = (id) => {
  if (!compareMode) return
  const index = selectedIds.value.indexOf(id)
  if (index > -1) {
    selectedIds.value.splice(index, 1)
  } else {
    if (selectedIds.value.length >= 2) {
      uni.showToast({ title: '最多选择两个对比', icon: 'none' })
      return
    }
    selectedIds.value.push(id)
  }
}

// 保存编辑
const saveItem = () => {
  if (!currentItem.value) return
  // 处理标签
  const tags = tagsInput.value.split(',').map(t => t.trim()).filter(Boolean)
  const index = knowledgeList.value.findIndex(item => item.id === currentItem.value.id)
  if (index > -1) {
    knowledgeList.value[index] = {
      ...knowledgeList.value[index],
      category: currentItem.value.category,
      tags: tags,
      notes: currentItem.value.notes
    }
  }
  saveData()
  updateCategoryList()
  showDetail.value = false
  uni.showToast({ title: '保存成功', icon: 'success' })
}

// 删除条目
const deleteItem = (id) => {
  uni.showModal({
    title: '确认删除',
    content: '确定要删除这条知识吗？',
    success: (res) => {
      if (res.confirm) {
        knowledgeList.value = knowledgeList.value.filter(item => item.id !== id)
        saveData()
        updateCategoryList()
        showDetail.value = false
        uni.showToast({ title: '已删除', icon: 'success' })
      }
    }
  })
}

// 页面加载/显示时刷新数据
onMounted(() => {
  loadData()
})
onShow(() => {
  loadData()
})
</script>

<style lang="scss" scoped>
.knowledge-page {
  display: flex;
  flex-direction: column;
  height: 100vh;
  background-color: #f5f5f5;
}

.top-bar {
  background-color: #fff;
  padding: 20rpx;
  border-bottom: 1rpx solid #eee;
}

.filter-row {
  display: flex;
  align-items: center;
  margin-bottom: 15rpx;
}

.category-scroll {
  flex: 1;
  white-space: nowrap;
}

.category-tag {
  display: inline-block;
  padding: 8rpx 24rpx;
  margin-right: 15rpx;
  background-color: #f0f0f0;
  border-radius: 30rpx;
  font-size: 26rpx;
  color: #333;
  &.active {
    background-color: #007aff;
    color: #fff;
  }
}

.compare-toggle {
  margin-left: 20rpx;
  padding: 6rpx 28rpx;
  font-size: 26rpx;
  background-color: #f0f0f0;
  border-radius: 20rpx;
  border: none;
  &.active {
    background-color: #ff9500;
    color: #fff;
  }
}

.search-box {
  margin-top: 10rpx;
}

.search-input {
  width: 100%;
  padding: 12rpx 20rpx;
  background-color: #f5f5f5;
  border-radius: 30rpx;
  font-size: 26rpx;
}

.knowledge-list {
  flex: 1;
  padding: 20rpx;
}

.empty-tip {
  text-align: center;
  color: #999;
  padding: 100rpx 0;
  font-size: 28rpx;
}

.knowledge-card {
  background-color: #fff;
  border-radius: 20rpx;
  padding: 25rpx;
  margin-bottom: 20rpx;
  box-shadow: 0 2rpx 10rpx rgba(0,0,0,0.03);
  &.selected {
    border: 2rpx solid #ff9500;
    background-color: #fff9f0;
  }
}

.card-header {
  display: flex;
  justify-content: space-between;
  margin-bottom: 12rpx;
}

.question {
  font-size: 30rpx;
  font-weight: bold;
  color: #333;
  flex: 1;
}

.time {
  font-size: 24rpx;
  color: #999;
  margin-left: 20rpx;
}

.card-answer {
  font-size: 26rpx;
  color: #666;
  margin-bottom: 15rpx;
  line-height: 1.5;
}

.card-footer {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.tags {
  display: flex;
  flex-wrap: wrap;
}

.tag {
  background-color: #eaf2ff;
  color: #007aff;
  padding: 4rpx 16rpx;
  border-radius: 20rpx;
  font-size: 22rpx;
  margin-right: 10rpx;
}

.category {
  font-size: 24rpx;
  color: #999;
}

.compare-panel {
  position: fixed;
  bottom: 0;
  left: 0;
  right: 0;
  max-height: 60vh;
  background-color: #fff;
  border-top-left-radius: 30rpx;
  border-top-right-radius: 30rpx;
  padding: 30rpx;
  box-shadow: 0 -5rpx 20rpx rgba(0,0,0,0.1);
  z-index: 1000;
}

.compare-title {
  font-size: 32rpx;
  font-weight: bold;
  text-align: center;
  margin-bottom: 20rpx;
}

.compare-content {
  max-height: 40vh;
  display: flex;
  flex-direction: row;
}

.compare-column {
  flex: 1;
  padding: 0 10rpx;
  border-right: 1rpx solid #eee;
  &:last-child {
    border-right: none;
  }
}

.compare-item {
  margin-bottom: 15rpx;
}

.label {
  font-size: 24rpx;
  color: #999;
}

.value {
  font-size: 26rpx;
  color: #333;
  word-break: break-all;
}

.close-compare {
  margin-top: 20rpx;
  background-color: #ff9500;
  color: #fff;
  border-radius: 30rpx;
  font-size: 28rpx;
}

.detail-panel {
  background-color: #fff;
  border-radius: 20rpx;
  padding: 30rpx;
  width: 90vw;
  max-height: 70vh;
  overflow-y: auto;
}

.detail-question {
  font-size: 32rpx;
  font-weight: bold;
  margin-bottom: 15rpx;
}

.detail-answer {
  font-size: 28rpx;
  color: #666;
  margin-bottom: 25rpx;
  line-height: 1.6;
  white-space: pre-line;
}

.edit-section {
  margin-bottom: 20rpx;
}

.edit-label {
  font-size: 26rpx;
  color: #333;
  margin-bottom: 8rpx;
  display: block;
}

.edit-input, .edit-textarea {
  width: 100%;
  padding: 15rpx;
  background-color: #f5f5f5;
  border-radius: 10rpx;
  font-size: 26rpx;
}

.edit-textarea {
  height: 120rpx;
}

.detail-actions {
  display: flex;
  justify-content: space-between;
  margin-top: 30rpx;
}

.btn-delete {
  background-color: #ff3b30;
  color: #fff;
  border-radius: 30rpx;
  width: 45%;
}

.btn-save {
  background-color: #007aff;
  color: #fff;
  border-radius: 30rpx;
  width: 45%;
}
</style>