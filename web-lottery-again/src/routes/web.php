<?php

/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| Here is where you can register all of the routes for an application.
| It is a breeze. Simply tell Lumen the URIs it should respond to
| and give it the Closure to call when that URI is requested.
|
*/

$router->get('/', function () use ($router) {
    // return $router->app->version();
    return redirect(url('/index.html'));
});

$router->post('/user/register', 'UserController@register');
$router->post('/user/login', 'UserController@login');

$router->post('/lottery/info', 'LotteryController@info');
$router->post('/lottery/charge', 'LotteryController@charge');

$router->group(['middleware' => 'auth'], function () use ($router) {
    $router->get('/user/info', 'UserController@info');

    $router->post('/lottery/buy', 'LotteryController@buy');

    $router->post('/flag', 'FlagController@flag');
});
