CREATE DATABASE IF NOT EXISTS ctf;
use ctf;

CREATE TABLE IF NOT EXISTS users(
    id int AUTO_INCREMENT,
    user_id LONGTEXT NOT NULL,
    username LONGTEXT NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS notes(
    id int AUTO_INCREMENT,
    user_id LONGTEXT NOT NULL,
    note_id LONGTEXT NOT NULL,
    text LONGTEXT NOT NULL,
    title LONGTEXT NOT NULL,
    post_at  LONGTEXT NOT NULL,
    prv LONGTEXT NOT NULL,
    PRIMARY KEY (id)
);


insert into users
    (user_id, username)
VALUES
    ('ybou40tdq60gazo0y171lb8122sht32j', 'Jack'),
    ('8ui8cdj1m8xut77fx2sg1crtaw23cy2g', 'Alfred'),
    ('dvcrtx6416n8x0bpfc4frrhipogm8j0a', 'Cary'),
    ('3eudu0y1ej3hnpxo93a217s2u8xwk5n7', 'Carl'),
    ('zmwbi2j7c228g0i6bhjb7sl2z8clm80a', 'CVE Announcements'),
    ('7bdeij4oiafjdypqyrl2znwk7w9lulgn', 'admin'),
    ('9fakpnpveqdhk5gc6o9gxcq4m7eb2zv1', 'Jason'),
    ('dkc5lqh1139hc3dmhxkuczyrckc6fum6', 'Joseph');



insert into notes
    (user_id, note_id, text, title, post_at,prv)
VALUES
    ('ybou40tdq60gazo0y171lb8122sht32j', 'x8j4bflkebpnbolpbyhuaze3uxqvwzam','Remember to launch a new Christmas celebration page before December 21', 'New features go online','2021-01-15 02:27 UTC', 'False'),
    ('8ui8cdj1m8xut77fx2sg1crtaw23cy2g', 'gr81t8oal67cbwjpp0grbo26yzossfvh','Remember to buy new toys tomorrow', 'Tomorrow memo','2021-01-15 02:27 UTC', 'False'),
    ('dvcrtx6416n8x0bpfc4frrhipogm8j0a', 'uever7o6kevt11t4em9tee2klv4n2571', 'Let us go then, you and I, When the evening is spread out against the sky Like a patient etherized upon a table.', 'Poetry','2021-01-15 02:28 UTC','False'),
    ('3eudu0y1ej3hnpxo93a217s2u8xwk5n7', 'c5irv7aicycbomyjkf4ox9jxjwsfgod9', 'If among the waxwing.s flight, I describe unbroken light, I describe water among the sleep of birds. A wingbeat governing swift fluidities of form.', 'My dream','2021-01-15 02:28 UTC','False'),
    ('7bdeij4oiafjdypqyrl2znwk7w9lulgn', 'lj40n2p9qj9xkzy3zfzz7pucm6dmjg1u', 'Finally bought Nintendo new game!', 'Nice day!', '2021-01-15 02:29 UTC','False'),
    ('zmwbi2j7c228g0i6bhjb7sl2z8clm80a', 'vzvpyv1h6wf0aj2n816xianut2blu0y4', 'Account maintained by the CVE Team to update the community on CVE related announcement', 'CVE', '2021-01-15 02:30 UTC','False'),
    ('7bdeij4oiafjdypqyrl2znwk7w9lulgn', '8gjrwovok2jarvg38jvbq9uriheahi29', '*ctf{Y0u_Are_t3e_Master_of_3he_Time!}', 'oh!oh!oh!My secret?', '2021-01-15 02:30 UTC','True'),
    ('9fakpnpveqdhk5gc6o9gxcq4m7eb2zv1', '6mxesnyaqdtaj7tipr7enopo89c40msr', 'Thats so annoying?Thats so annoying?Thats so annoying?', 'Thats so annoying?', '2021-01-15 02:31 UTC','False'),
    ('7bdeij4oiafjdypqyrl2znwk7w9lulgn', 'kb01u16uafqr55hartkv6xophznwzkbg', 'Remember to go to art class tomorrow.', 'Remember?', '2021-01-15 02:32 UTC','False'),
    ('dkc5lqh1139hc3dmhxkuczyrckc6fum6', 'bz9kwxxp5egfn6b82q8l95x8oe7p6v9b', 'Happy birthday!', 'Happy birthday!', 'Happy birthday!', 'False');

ALTER TABLE users CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;
ALTER TABLE notes CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;