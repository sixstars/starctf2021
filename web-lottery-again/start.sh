#!/bin/bash

docker-compose up -d nginx mysql php
docker-compose exec php php artisan migrate
