'use strict';

// Declare app level module which depends on views, and components
angular.module('myApp', [
    'ngRoute',
    'ui.router',
    'myApp.home',
    'myApp.view1',
    'myApp.view2',
    'myApp.version'
])
.config(['$locationProvider',
         '$routeProvider',
         function($locationProvider, $routeProvider,
                  $stateProvider, $urlRouterProvider, $interpolateProvider,
                  $httpProvider, $resourceProvider) {
             $locationProvider.hashPrefix('!');
             $routeProvider.otherwise({redirectTo: '/home'});
             $locationProvider.html5Mode(true);
             
}])
    .controller('AppController',
                function AppController($scope, $rootScope, $location,
                                       $http, $log, $stateParams, $state){
                    
                    $scope.message = "I am just testing ";
                    $scope.init = function(){
                        console.log("Here is something you might be interested!");
                    }
        
    })
;
