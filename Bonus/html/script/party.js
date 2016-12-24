var prefix_link = "rtype: ";
var room_name = "";

function CreateDivParty(party) {
    var div = '<div class="mdl-card rtype mdl-cell mdl-cell--12-col">\n';
    div += '<div class="mdl-card__media mdl-color-text--grey-50">\n';
    div += '<h3 class="party_name">' + party.name + '</h3>\n';
    div += '</div>\n';
    div += '<div class="mdl-card__supporting-text mdl-color-text--grey-600">\n';
    div += 'Players: ' + party.nbPlayers + '/4 <br>';
    div += 'Protected: ' + party.pwdPresent + '<br>';
    div += 'Runnings: ' + party.running + '<br>';
    div += '</div>';
    div += '<div class="mdl-card__supporting-text meta mdl-color-text--grey-600">';
    div += '<a href="#" onclick="showConnectModal(\'' + party.name + '\');return false;" class="demo-nav__button connect_btn" title="Connect">';
    div += 'Connect ';
    div += '<button class="mdl-button mdl-js-button mdl-js-ripple-effect mdl-button--icon" data-upgraded=",MaterialButton,MaterialRipple">';
    div += '<i class="material-icons" role="presentation">arrow_forward</i>';
    div += '<span class="mdl-button__ripple-container"><span class="mdl-ripple is-animating"></span></span>'
    div += '</button></a></div></div>';
    return div;
}

function CreateRoom() {
    $.get('/CreateParty?name=' + $('#Room_Create_Txt').val() + '&password=' + $('#Pass_Create_Txt').val(), (ret) => {
        if (ret.success) {
            setTimeout(() => {
                UpdateParty();
                closeModal('#CreateParty_Modal');
            }, 700);
        }
    });
}

function connectParty() {
    window.open(prefix_link + $('#User_Connect_Txt').val() + room_name + $('#Pass_Connect_Txt').val());
}

function UpdateParty() {
    $.get('/GetParty', (ret) => {
        if (ret.success) {
            $('content').html('');
            ret.Party.forEach(function (elem, index) {
                $('content').append(CreateDivParty(elem));
            });
        }
    });
}