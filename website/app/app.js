'use strict';

// Declare app level module which depends on views, and components
angular.module('myApp', [
    'ngRoute',
    'ui.router',
    'myApp.home',
    'myApp.people',
    'myApp.publications',
    'myApp.version'
])
    .config(['$locationProvider',
             '$routeProvider',
             function($locationProvider, $routeProvider,
                      $stateProvider, $urlRouterProvider, $interpolateProvider,
                      $httpProvider, $resourceProvider) {
                 $locationProvider.hashPrefix('!');

                 $routeProvider
                     .when('/people', {
                         templateUrl : 'people/people.html',
                         controller  : 'PeopleController'
                     })
                     .when('/', {
                         templateUrl : 'home/home.html',
                         controller  : 'HomeController'
                     })
                     .when('/home', {
                         templateUrl: 'home/home.html',
                         controller: 'HomeController'
                     })
                     .when('/publications', {
                         templateUrl: 'publications/publications.html',
                         controller: 'PublicationController'
                     })
                     .otherwise({redirectTo: '/home'});
                 $locationProvider.html5Mode(true);

             }])
    .controller('AppController',
                function AppController($scope, $rootScope, $location,
                                       $http, $log, $stateParams, $state){

                    $scope.message = "I am just testing ";
                    $scope.init = function(){
                        console.log("Here is something you might be interested!");
                    };
                })
;
