FROM python:3.6.0-alpine

COPY ./source /app
WORKDIR /app

RUN pip3 install pyftpdlib -i https://pypi.tuna.tsinghua.edu.cn/simple

EXPOSE 8877
CMD python3 ftp-server.py