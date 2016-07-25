angular.module('myApp.Home', ['ngRoute'])
.config(['$routeProvider', function($routeProvider) {
    $routeProvider.when('/home', {
        templateUrl: 'home/home.html',
        controller: 'HomeController'
    });
}])
.controller('HomeController', [function() {
    console.log("something is happening");
    // this is for the home page of the website.    
}]);



