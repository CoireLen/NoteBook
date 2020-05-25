# 反向代理
配置/etc/nginx/nginx.conf
```
upstream python_server_2{
    server 127.0.0.1:5001 weight=4 max_fails=2 fail_timeout=30s;
    }
server {
        listen       80;
        server_name  depice.cn;

        location / {
            proxy_pass http://python_server_2;
	    proxy_set_header X-Forwarded-For $remote_addr;
        }
	
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   /srv/www/htdocs/;
        }

    }
```