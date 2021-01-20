FROM python:3.6.0-alpine

COPY ./source /app
WORKDIR /app

COPY flag_728246ee4be43072f63a6d4bb5ddb6b0c705e8e6 /flag_728246ee4be43072f63a6d4bb5ddb6b0c705e8e6
COPY readflag /readflag
RUN chmod 555 /readflag
RUN chmod u+s /readflag
RUN chmod 500 /flag_728246ee4be43072f63a6d4bb5ddb6b0c705e8e6

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories
RUN apk add -U curl

RUN apk add -U gcc && \
    apk add -U libc-dev

RUN pip3 install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple
RUN rm requirements.txt

RUN addgroup -S app && adduser -S app -G app
USER app

EXPOSE 5000
CMD gunicorn -b 0.0.0.0:5000 -w 6 --threads 6  --log-level 'debug' app:app
