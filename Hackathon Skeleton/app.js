// Sets console.log() to print to Evothings console
//test
if (window.hyper && window.hyper.log) { console.log = hyper.log }

document.addEventListener(
    'deviceready',
    function() { /*TODO: Add your callback here*/ });

var app = {}

app.SERVICE_UUID='0000ffe0-0000-1000-8000-00805f9b34fb';
app.CHARACTERISTIC_UUID='0000ffe1-0000-1000-8000-00805f9b34fb';

app.showControls = function()
{
    $('#disconnect').prop('disabled', false);
    $('#startView').hide();
    $('#controlsView').show();
}

app.showStart = function()
{
    $('#disconnect').prop('disabled', true);
    $('#startView').show();
    $('#controlsView').hide();
}

function pressButton(elementid, callback){
    let theid = elementid;
    document.getElementById(`${theid}`).style.backgroundColor = 'goldenrod';
    callback();
}

function unpress(elementid){
    let theid = elementid;
    document.getElementById(`${theid}`).style.backgroundColor = 'skyblue';
}

document.addEventListener( 
    'deviceready',
    function () {
        app.initialize();
    }
);

app.initialize = function () {
    console.log('Initialized');
    app.connected = false;
    app.device = null;
}

app.connect = function () {
    console.log('Attempting to connect to bluetooth module');

    evothings.easyble.startScan(scanSuccess, scanFailure, { serviceUUIDS: [app.SERVICE_UUID] }, { allowDuplicates: false });
}

function scanSuccess(device) {
    if (device.name != null && device.address=='424002B5-7FD1-E4D7-673A-726F525D26C3') {
        console.log('Found' + device.name);
        device.connect(connectSuccess, connectFailure);
        evothings.easyble.stopScan();
    }
}

function scanFailure(errorCode) {
    console.log('Error ' + errorCode);
}

function connectSuccess(device) {
    console.log('Successfully connected!!');
    app.connected = true;
    app.device = device;
    app.device.readServices(serviceSuccess, serviceFailure, [app.SERVICE_UUID]);
}

function connectFailure() {
    app.connected = false;
    console.log('Failed to connect! :( ');
}

app.disconnect = function (errorMessage) {
    if (errorMessage) {
        console.log(errorMessage);
    }
    app.connected = false;
    app.device = null;

    evothings.easyble.stopScan();
    evothings.easyble.closeConnectedDevices();
}

function serviceSuccess(device) {
    console.log('The bluetooth module can now read and write');
    app.device.enableNotification(
        app.SERVICE_UUID,
        app.CHARACTERISTIC_UUID,
        app.receivedData,
        function (errorCode) {
            console.log('Failed to receive notification from device' + errorCode);
        },
        { writeConfigDescriptor: false }
    );
}

function serviceFailure(errorCode) {
    console.log('Failed to read services' + errorCode);
    app.disconnect();
}

app.sendData = function (data) {
    if (app.connected && app.device != null) {
        data = new Uint8Array(data);
        app.device.writeCharacteristic(
            app.CHARACTERISTIC_UUID,
            data,
            function () {
                Console.log('Succeed to send message!' + data);
            },
            function (errorCode) {
                Console.log('Failed to send message!' + errorCode);
            }
        );
    }
    else {
        app.disconnect('Device was disconnected when trying to send message');
    }
}

app.receivedData = function (data) {
    if (data == 0x16 ) {  

    }
}

function BaseTurnLeft() {
    console.log("BaseTurnLeft called");
}

function BaseTurnRight() {
    console.log("BaseTurnRight called");
}

function BaseForward() {
    console.log("BaseForward called");
}

function BaseBackward(){
    console.log("BaseBackward called");
}

function ShoulderUp() {
    console.log("ShoulderUp called");
}

function ShoulderDown() {
    console.log("ShoulderDown called");
}

function ElbowFoward() {
    console.log("ElbowForward called");
}

function ElbowBackward() {
    console.log("ElbowBackward called");
}

function WristTurnLeft() {
    console.log("WristTurnLeft called");
}

function WristTurnRight() {
    console.log("WristTurnRight called");
}

function Grip() {
    console.log("Grip called");
}

function Release() {
    console.log("Release called");
}

function pressStart() {
    document.getElementById("startView").style.display="none";
    document.getElementById("controlsView").style.display="";
}
