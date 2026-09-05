# MoeTcpClient TCP客户端

## 引入方式

```javascript
const moeTcpClient = uni.requireNativePlugin("moe-tcp-client");
```

## 方法

### 建立连接
```javascript
MoeTcpClient.connect({
  ip: 'xxx.xxx.xxx.xxx',
  port: 6900
}, result => {
  // 连接结果
})
```

### 断开连接
```javascript
MoeTcpClient.disconnect();
```

### 判断是否处于连接
```javascript
MoeTcpClient.isConnected(res => {

});
```

### 发送字符串消息
```javascript
MoeTcpClient.sendStr({
  message: '发送的内容'
});
```

### 发送Hex字符串消息
```javascript
MoeTcpClient.sendHexStr({
  message: '发送的内容'
});
```

## 注册消息监听

### 监听服务端消息
```javascript
MoeTcpClient.onReceive(res => {
    
});
```

### 监听通讯断连
```javascript
MoeTcpClient.onDisconnect(res => {

});
```

### 服务端消息res返回值示例说明

```
{
    "code": 1,
    "data": "FF001122CCDD",
    "dataBinary": "RkYwMDExMjJDQ0REDQo=",
    "msg": "收到消息"
}
```

| 字段 | 字段类型 | 解析备注 |
| --- | --- | --- |
| code | int | 错误码：1正常、0失败 |
| msg | String | 消息反馈 |
| data | String | 消息数据（字节流UTF8编码后的字符串） |
| dataBinary | String | 消息数据原始字节流（uniapp会自动编码成base64字符串） |

> 如果服务端消息是文本消息，使用data即可
> 如果服务端消息是十六进制数据，为防止编码问题，可直接使用 dataBinary 转换

下面给出一个常用的base64字符串转Hex字符串方法
```javascript
/**
 * base64字符串转Hex字符串
 * @params base64Str
 */
let base64ToHexStr = function(base64Str){
  let binaryStr = atob(base64Str);
  let hexStr = '';
  for (let i = 0; i < binaryStr.length; i++) {
    let hex = binaryStr.charCodeAt(i).toString(16);
    hexStr += ('0' + hex).slice(-2);
  }
  return hexStr;
}
```