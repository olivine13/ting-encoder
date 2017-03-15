# ting-encoder
一个小的加密库，目前使用rc4，已经接入aes暂未设计接口
加密解密为双向，即对密文加密后即为原文

该项目使用c++编写，能够在多平台编译使用

## Usage

### android
从本地文件中解密或加密  
crypt or decrypt from local disk  
`
EncoderUtil.cryptFromLocal(String path);
`
---  
从assets中加密or解密  
crypt or decrypt from assets  
`
EncoderUtil.cryptFromAssets(Context context,String path);
`
---  
从字节数组加密or解密  
crypt or decrypt from byte array  
`
EncoderUtil.crypt(byte[] buffer);
`

### OSX or Linux
#### Compile  #

```  
cd build
cmake ..
make
```

#### Help
输入-h查看帮助

#### Crypt(Decrypt) File  
-o为可选项，如未输入则在当前目录生成加密后文件  
`
encoder -i [src file path] -o [dst file path]
`