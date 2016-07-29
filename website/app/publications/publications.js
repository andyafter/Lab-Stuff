'use strict';

angular.module('myApp.publications',
               ['ngRoute',
                'ui.router',
                'myApp'
               ])

.config(['$routeProvider', function($routeProvider) {
  $routeProvider.when('/publications', {
    templateUrl: 'publications/publications.html',
    controller: 'PublicationController'
  });
}])

.controller('PublicationController', [function() {
    
}]);
