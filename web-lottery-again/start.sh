#!/bin/bash

docker-compose run composer install
docker-compose up -d nginx mysql php
sleep 10
docker-compose exec php php artisan migrate
