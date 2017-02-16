var app = angular.module('App', []);

app.controller('Controller', function($scope, $http) {
    $http.get("menu.json")
        .then(function (response) {$scope.names = response.data.Navigation;});
});

app.controller("seancesCtrl", function($scope, $http, $sce) {
    $http.get("seances.json")
        .then(function(response) {
        $scope.seances = angular.forEach(response.data, function (seance, index, tableau) {
            tableau[index] = angular.forEach(seance, function(valeur, cle, tableau) {
                tableau[cle] = $sce.trustAsHtml(valeur);
            });
        });
    });
});