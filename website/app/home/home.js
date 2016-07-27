angular.module('myApp.home',
               ['ngRoute'])
.config(['$routeProvider', function($routeProvider) {
    $routeProvider.when('/home', {
        templateUrl: 'home/home.html',
        controller: 'HomeController'
    });
}])
.controller('HomeController', [function($scope) {
    console.log("something is happening");
    // this is for the home page of the website.
    $scope.init = function(){
        console.log("Something is definitely happening!");
    }
}]);



