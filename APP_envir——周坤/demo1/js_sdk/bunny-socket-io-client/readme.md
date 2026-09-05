# bunny-socket-io-client
### 开发文档
[UTS 语法](https://uniapp.dcloud.net.cn/tutorial/syntax-uts.html)
[UTS API插件](https://uniapp.dcloud.net.cn/plugin/uts-plugin.html)
[UTS 组件插件](https://uniapp.dcloud.net.cn/plugin/uts-component.html)
[Hello UTS](https://gitcode.net/dcloud/hello-uts)

#### 支持

基于[socket.io-client-java:2.1.0](https://github.com/socketio/socket.io-client-java)

支持的socket.io服务端

| Client version | Socket.IO server |
| -------------- | ---------------- |
| 0.9.x          | 1.x              |
| 1.x            | 2.x              |
| 2.x            | **3.x / 4.x**    |

#### 使用

```ts
import { SOCKET_IO_CLIENT, OPTIONS } from "@/uni_modules/bunny-socket-io-client"

const map : Map<string, Array<string>> = new Map<string, Array<string>>()
map.set("tokne", ["9999", "8882222"])
const opt : OPTIONS = {
    path: "/v1/socket",
    query: "id=0&it1",
    extraHeaders: map
}
const so = new SOCKET_IO_CLIENT("ws://192.168.1.199:7004", opt)
so.on("send_end_data", (option : object | null) => {
    console.log("声明的回调", option)
})
so.connect()
so.emit("test1", "asdfasdfasdfasdfasdfasf")
// so.close()
```

emit 受限于uts不定长参数，目前只支持一个字符串类型的参数。后续会继续跟进更新。

创建会生成全新的连接，根据业务需求考虑是否需要单例函数来生成socket对象

OPTIONS 目前支持属性

```ts
export type OPTIONS = {
	path ?: string
	query ?: string
	forceNew ?: boolean
	multiplex ?: boolean
	extraHeaders ?: Map<string, Array<string>> | null
}
```
OPTIONS 的默认属性（从文档直接复制）

```java
IO.Options options = IO.Options.builder()
    // IO factory options
    .setForceNew(false)
    .setMultiplex(true)

    // low-level engine options
    .setTransports(new String[] { Polling.NAME, WebSocket.NAME })
    .setUpgrade(true)
    .setRememberUpgrade(false)
    .setPath("/socket.io/")
    .setQuery(null)
    .setExtraHeaders(null)

    // Manager options
    .setReconnection(true)
    .setReconnectionAttempts(Integer.MAX_VALUE)
    .setReconnectionDelay(1_000)
    .setReconnectionDelayMax(5_000)
    .setRandomizationFactor(0.5)
    .setTimeout(20_000)

    // Socket options
    .setAuth(null)
    .build();
```

#### 致谢

感谢 @DCLoud_Android_DQQ 提供的uts技术支持

