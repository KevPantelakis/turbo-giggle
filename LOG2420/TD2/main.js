$(function() {

    $("#baconButton").click(function() {
        if(!$(this).disabled) {
            var textc = $("#awesomeness-container");
            $.getJSON('http://baconipsum.com/api/?callback=?',
                { 'type':'meat-and-filler', 'start-with-lorem':'1', 'paras':'3' },
                function(baconGoodness)
                {
                    if (baconGoodness && baconGoodness.length > 0)
                    {
                        textc.val('');
                        for (var i = 0; i < baconGoodness.length; i++)
                            textc.val(textc.val() + baconGoodness[i]);
                        textc.show();
                    }
                });
        }
    });
    //Bacon Bacon Bacon

    var w = undefined;

    $('#count').click(function (){
        if(!$(this).hasClass('disabled')){
            $(this).addClass('disabled');
            w = new Worker('worker.js');
            $('#pgb').addClass('active');
            $("#awesomeness-container").prop("disabled", true);
            $('#baconButton').addClass('disabled');
            w.onmessage = function(event){
                $('#word-count').html('Auctual count : ' + event.data[0]);
                $('#pgb').html(event.data[1] + '%');
                $('#pgb').css('width', event.data[1]+'%');
                if(event.data[1] <= 45){
                    $('#pgb').addClass('progress-bar-success');
                    $('#pgb').removeClass('progress-bar-danger');
                }
                else if(event.data[1] <= 80){
                    $('#pgb').addClass('progress-bar-warning');
                    $('#pgb').removeClass('progress-bar-success');
                }
                else{
                    $('#pgb').addClass('progress-bar-danger');
                    $('#pgb').removeClass('progress-bar-warning');
                }


                if(event.data[1] == 100){
                    $('#pgb').removeClass('active');
                    $('#count').removeClass('disabled');
                    $('#baconButton').removeClass('disabled');
                    $("#awesomeness-container").prop("disabled", false);
                    w.terminate();
                    w = undefined;
                }
            };
            var text = $('#awesomeness-container').val();
            if(text) {
                var url = text.match(/^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$/);
                if(url){
                    text = '';
                    for(var u of url){
                        $.get(u, 'false', 'nom_fonction_retour', 'text');
                    }
                }
                w.postMessage(text);
            }
        }
    });

    function success (html){
        text = text + html;
    }

    $('#cancel').click(function(){
        if($('#count').hasClass('disabled')){
            w.terminate();
            w = undefined;
        }
        $('#pgb').removeClass('active');
        $('#count').removeClass('disabled');
        $('#baconButton').removeClass('disabled');
        $('#word-count').html('You saddly don\'t have any token... :(');
        $('#pgb').html('N/A');
        $('#pgb').css('width', '0%');
        $("#awesomeness-container").prop("disabled", false);


    });

    $('#clear').click(function(){
        if($('#count').hasClass('disabled')){
            w.terminate();
            w = undefined;
        }
        $('#awesomeness-container').val('');
        $('#pgb').removeClass('active');
        $('#count').removeClass('disabled');
        $('#baconButton').removeClass('disabled');
        $("#awesomeness-container").prop("disabled", false);
    });

});