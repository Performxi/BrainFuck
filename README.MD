BrainFuck
==============
BrainFuck 是一门小巧的类似图灵机的语言，程序由`+-><[].,` 八个符号组成，具体规则如下。

* 首先有一条环形的纸带，纸带分成一些小格，格子上只能是0-255中间的某一个数（默认是0）。
* 有一只铅笔，笔尖指向第一个格子（或者说随便一个，因为是环形的：）。
* 一个由`+-><[].,` 八个符号组成的字符序列（源代码）。
* 从源代码的第一个字符读起：
  * 如果是`+`的话，当前笔尖指向的格子数字加一。（溢出的话：255+1=0）
  * `-`就减一（0-1=255）
  * `>`笔尖向右移动一格，`<`向左移动一格。
  * `.`输出当前格子上的数字
  * `,` 输入一个数字到当前格子
  * `[` 如果当前格子不为零的话，继续执行下一个命令，不然的话跳转到与之对应的`]`。
  * `]` 与`[`相反。
## 例子：
### 归0
`[+]` 或者`[-]`可以把当前的数字清0.
### 右移加
`[->+<]>`把#1和#2 的格子相加到#2,#1归0.

或者可以这样描述：
```
input: *a,b
output: a=0,*b=a+b
code:[->+<]>
```
### 复制加
同样是把#1加到#2 ，不过#1的数据会保留，需要#3 来做暂存区。
描述如下：
```
input: *a,b,c=0
output: *a=a,b=a+b,c=0
code:[->+>+<<]>>[-<<+>>]<<
```

### 乘法
多次使用`复制加`实现乘法
```
input:*T,a,b=0,c=0
output: T=0,a=a,*b=a*T,c=0
code:[->   [->+>+<<]>>[-<<+>>]<<  <] >>
```
注意到中间有一段`[->+>+<<]>>[-<<+>>]<<`就是上面的“复制加”的代码，所以我们可以引入记号`(cp+)`来代表`[->+>+<<]>>[-<<+>>]<<`，这样乘法的代码就变成`[->(cp+)<]>>`。

用特定的解析器可以把这些记号解析成纯brainfuck的代码。

###取布尔值
取指定格子的布尔值（0就是False，其他的就是True（1））

```
input:*a,b=0
output:a=0,*b=bool(a)
code:[>+<[-]]>
```

### 取反
0变成1，1变成0

``` 
input: *a=[0,1],b=0
output: a=0,*b=not a 
code:>+<[>-<[-]]>
```

### 与门

如果#1，#2同时为true的话，#3 为true，否则为false

```
input : *a,b,T
output: a=0,b=0,*T=a&&b
code: [>[>+<[-]]<[-]]>>
```

或者

```
input: *a,b,T
output : a=a,b=0,*T=a&&b
code : [>[>+<[-]]]>
```

还有一种不用#3的

```
input : *a,b
output : *a=a&&b,b=0
code : [[-]>[<+>][-]]<
```



usage
======================
在`src`目录下是用c写的解释器,make一下就可运行。

### bf_base.c
这个是最基础版的解释器。
