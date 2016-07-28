angular.module('myApp.home',
               ['myApp',
                'ngRoute',
                'ui.router',])
    .config(['$routeProvider',
             function($routeProvider) {
                 
             }])
    .controller('HomeController', ['$scope',function($scope) {
        // this is for the home page of the website.
        $scope.init = {};
        $scope.init = function() {
            console.log("something is happening");
        };
    }]);
