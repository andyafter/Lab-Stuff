angular.module('myApp.projects', ['ngRoute',
                                  'myApp'])

    .config(['$routeProvider', function($routeProvider) {
        $routeProvider.when('/projects', {
            templateUrl: 'projects/projects.html',
            controller: 'ProjectsController'
        });
    }])

    .controller(
        'ProjectsController',
        ['$scope',
         function($scope) {
             $scope.init = function(){
                 console.log("This is initiation from Projects!");
             }
         }]);
