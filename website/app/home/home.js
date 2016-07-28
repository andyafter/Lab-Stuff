angular.module('myApp.home',
               ['myApp',
                'ngRoute',
                'ui.router',])
    .config(['$routeProvider',
             function($routeProvider) {
                 $routeProvider
                     .when('/', {
                         templateUrl : 'home/home.html',
                         controller  : 'HomeController'
                     })
                     .when('/home', {
                         templateUrl: 'home/home.html',
                         controller: 'HomeController'
                     });
             }])
    .controller('HomeController', ['$scope',function($scope) {
        // this is for the home page of the website.
        $scope.init = {};
        $scope.init = function() {
            console.log("something is happening");
        };
    }]);
