# file_hash_helper 

## 软件简介

- 计算文件哈希值
- 复制计算结果
- 与参考值比对显示比对结果
- 导出文件哈希值为txt文件
- 支持MD5, SHA-1, SHA-224, SHA-256, SHA-384, SHA-512共六种常见哈希算法

## 软件截图

- 主界面

![主界面](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E4%B8%BB%E7%95%8C%E9%9D%A2.png)


- 计算中

![计算中](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E8%AE%A1%E7%AE%97%E4%B8%AD1.png)

![计算中](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E8%AE%A1%E7%AE%97%E4%B8%AD2.png)


- 计算完成

![计算完成](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E8%AE%A1%E7%AE%97%E5%AE%8C%E6%88%90.png)


- 比对成功

![比对成功](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E6%AF%94%E5%AF%B9%E6%88%90%E5%8A%9F.png)


- 比对失败

![比对失败](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E6%AF%94%E5%AF%B9%E5%A4%B1%E8%B4%A5.png)


- 复制结果

![复制结果](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E5%A4%8D%E5%88%B6%E7%BB%93%E6%9E%9C.png)


- 导出界面

![导出界面](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E5%AF%BC%E5%87%BA%E7%95%8C%E9%9D%A2.png)


- 导出中

![导出中](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E5%AF%BC%E5%87%BA%E4%B8%AD1.png)

![导出中](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E5%AF%BC%E5%87%BA%E4%B8%AD2.png)


- 导出成功

![导出成功](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E5%AF%BC%E5%87%BA%E6%88%90%E5%8A%9F.png)


- 导出文件

![导出文件](https://github.com/kaiza-hikaru-del/file_hash_helper/raw/main/software%20picture/%E5%AF%BC%E5%87%BA%E6%96%87%E4%BB%B6.png)


## 尚未完成功能（暂不确定是否加入）

1. “x”-左/右上角关闭-按下后强制结束一切活动

	- 目前按下"x"后可能尚无法完全结束程序
	- 由于没有对close()进行重写
	- 因此使用时尽量避免未计算完成便关闭程序窗口

  

2. 按下“开始校验”按钮后仅冻结会造成线程冲突的控件

	- 目前按下“开始校验”按钮后会冻结整个主窗口
	- 简单地解决了线程间可能出现的数据冲突问题
	- 但同时造成主窗口不能响应不造成影响的其他信号