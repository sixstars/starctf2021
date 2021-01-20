FROM python:alpine3.6

COPY ./app /app
WORKDIR /app

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories

ENV PYTHONUNBUFFERED=0

RUN pip install -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple
RUN rm requirements.txt



EXPOSE 5000

CMD gunicorn -b 0.0.0.0:5000 -w 6 --threads 6  --log-level 'debug' app:app
