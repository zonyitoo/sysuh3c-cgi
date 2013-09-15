# Login CGI for CLI H3C
[CLI H3C](https://github.com/zonyitoo/clih3c) is a H3C client.

## Depencences
* uhttpd
* libc
* libgcc

## Compile

* First you should get the **OpenWRT-SDK**. See [here](http://wiki.openwrt.org/zh-cn/doc/howto/obtain.firmware.sdk) for more detail.

* Then `cd` into the SDK Directory.

```bash
git clone git@github.com:zonyitoo/sysuh3c-cgi.git package/syush3c-cgi
make
```

* You will get the `sysuh3c-cgi_[version]-1_[arch].ipk` in `bin/[arch]/package`

## Usage

* Start the `uhttpd` daemon.
```bash
/etc/init.d/uhttpd enable
/etc/init.d/uhttpd start
```

* Open your browser, visit the URL: `http://192.168.1.1/cgi-bin/sysuh3c.cgi`

*It supports all mobile phone.*

## Screenshot
![screenshot](https://raw.github.com/zonyitoo/sysuh3c-cgi/master/screenshot.png)
