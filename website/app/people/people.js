'use strict';

angular.module('myApp.people', ['ngRoute'])

    .config(['$routeProvider', function($routeProvider) {
        $routeProvider.when('/people', {
            templateUrl: 'people/people.html',
            controller: 'PeopleController'
        });
    }])

    .controller('PeopleController', ['$scope',
        function($scope) {
            $scope.init = function(){
                console.log("This is initiation from People!");
            }
        }]);
