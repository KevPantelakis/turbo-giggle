var map;				//Variable contenant l'élément Map
var marker = null;      //Variable faisant office de marqueur
var infoWindow = null;  //Information sur la ville
var zoomFactor = 8;		//variable pour le zoom: 0= world, 5=landmass/continent, 10=cities, 15=streets, 20=buildings
var cities = [];        //Tableaux de tout les noms de villes compris dans le JSON
var cities_info ;       //Contient touts les informations sur les villes

// Regex pour un input :
// de format "latitude, longitude" ou de format "latitude,longitude"
var reglatlng = /^-?[1-8]?[0-9](\.\d{1,6})?,\ ?-?[1-1]?[0-9]?[0-9](\.\d{1,6})?$/i;

// Variable pour modifier l'apparence de la carte googlemap, dans ce cas ci elle met les routes en gris
var styleArray = [
    {
        stylers: [
            { saturation: 10 }
        ]
    },{
        featureType: "road",
        elementType: "geometry",
        stylers: [
            { lightness: 90 },
            { visibility: "on" },
            {color: "#aaabab"}
        ]
    }
];

//Initialise la carte googlemap avec quelques paramètres.
function initMap() {
    map = new google.maps.Map(document.getElementById('map'), {
        center: {lat: 45.5, lng: -73.550003}, // centre la carte
        zoom: zoomFactor,                     // définit le zoom initial
        disableDefaultUI: true,               // déactive 'interface utilisateur
        draggable:true,
        styles: styleArray,                   // Modifie l'apparance de la carte selon le tableau styleArray
    });
}
initMap();					//Initialisation de la Map avec l'api de google map



$(document).ready(function(){

    // On "parse" le fichier villes.json et on met les information dans cities_info et cities
    $.getJSON("villes.json").done(function(data){
        cities_info = data;

        for(var city in cities_info){
            cities.push(city);
        }


    });

    $('.slider-val').html(zoomFactor); // met à jour le texte du facteur de zoom sur la page

    // controle du slider
    $( '#slider').slider({
        orientation: "horizontal",
        range: "min",
        min: 2,
        max: 20,
        value: 8,
        slide: function( event, ui ) {
            $( ".slider-val" ).html( ui.value );
            zoomFactor = ui.value;
            map.setOptions({zoom:zoomFactor});
        }
    });

    $("#latlng").click(function(event){
        if(reglatlng.exec($("#autocomplete").val())) {
            var coordinates = $("#autocomplete").val().split(",");
            if(coordinates[0] <= 85 && coordinates[0] >= -85.05115) {
                if(coordinates[1] <= 180 && coordinates[0] >= -180){
                    var pos = new google.maps.LatLng(coordinates[0], coordinates[1]);
                    map.setCenter(pos);
                    if (marker !== null) {
                        marker.setMap(null);
                    }
                    marker = new google.maps.Marker({
                        position: pos,
                        map: map,
                        animation: google.maps.Animation.DROP,
                    });
                    $('#status').css("color", "black");
                    $('#statusfr').css("color", "black");
                    $('#statusfr').html('Latitude: ' + coordinates[0].value + ' ' + 'Longitude: ' + coordinates[1].value);
                    $('#status').html('Latitude: ' + coordinates[0] + ' ' + 'Longitude: ' + coordinates[1]);
                    $("#autocomplete").val('');
                    return false;
                }else{
                    $('#status').css("color", "red");
                    $('#statusfr').css("color", "red");
                    $('#statusfr').html('Mauvais respect des bornes sur la longitude [-180 , 180] ');
                    $('#status').html('Wrong bonds for longitude: [-180 , 180]');
                }
            }else{
                $('#statusfr').css("color", "red");
                $('#status').css("color", "red");
                $('#statusfr').html('Mauvais respect des bornes sur la latitude [-85.05115 , 85] ');
                $('#status').html('Wrong bonds for latitude: [-85.05115 , 85]');
            }
        }else{
            $('#status').css("color", "red");
            $('#statusfr').css("color", "red");
            $('#statusfr').html('Mauvais format pour les coordonées');
            $('#status').html('Wrong coordinates format');
        }
    });

    // Fonctionalités du auto complete
    $( "#autocomplete" ).autocomplete({
        autoFocus: true, // surligne le résultat le plus pertinant en tout temps
        source: cities,  // tableau qui sert de liste pour le auto complete

        // On trouve la longitude et la latitude de la ville et on centre la vue sur cette position en plus d'afficher
        // un marqueur de location
        select: function (event,ui){

            var pos = new google.maps.LatLng(cities_info[ui.item.value].lat, cities_info[ui.item.value].lon);
            map.setCenter(pos);
            if(marker !== null){
                marker.setMap(null);
            }
            marker = new google.maps.Marker({
                position: pos,
                title:ui.item.value,
                map: map,
                animation: google.maps.Animation.DROP,
            });
            $('#status').css("color", "black");
            $('#statusfr').css("color", "black");
            $('#statusfr').html('Vous avez sélectionné: ' + ui.item.value);
            $('#status').html('You\'ve selected: ' + ui.item.value);
            $(this).val('');
            return false;
        }
    });

    $('#toggle-fr').click(function(){
        $('.anglais').hide();
        $('.francais').show();
    });

    $('#toggle-en').click(function(){
        $('.francais').hide();
        $('.anglais').show();
    });

});
