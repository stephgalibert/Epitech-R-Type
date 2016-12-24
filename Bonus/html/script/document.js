function resize() {
    var height = ($(window).height() - $('footer').height()) - (80 * 2 + 230);
    $('content').css('min-height', height);
}

function closeModal(modal) {
    $(modal)[0].close();
}

function showConnectModal(party_name) {
    room_name = party_name;
    var connectiondialog = document.querySelector('#Connection_Modal');
    connectiondialog.showModal();
}

$(document).ready(() => {
    var connectiondialog = document.querySelector('#Connection_Modal');
    var createparty_modal = document.querySelector('#CreateParty_Modal');
    resize();
    $('.refresh_party').click(() => {
        UpdateParty();
    });
    $('.add_party').click(() => {
        createparty_modal.showModal();
    });
    $('.connect_btn').click(() => {
        alert($(this).attr('party_name'));
    });
    if (!connectiondialog.showModal) {
        dialogPolyfill.registerDialog(connectiondialog);
    }
    if (!createparty_modal.showModal) {
        dialogPolyfill.registerDialog(createparty_modal);
    }

});

$(window).resize(() => {
    resize();
});