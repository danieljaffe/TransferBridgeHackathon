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
    
    if (device.name != null && device.address=='D479B6B9-D64B-9AD7-72E1-B96D1D670E5C') {
        console.log('Found' + device.name + device.address);
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
                console.log('Succeed to send message!' + data);
            },
            function (errorCode) {
                console.log('Failed to send message!' + errorCode);
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

let buttonOff = false;
buttonOff = document.addEventListener('touchend', function(){
    console.log("finger removed");
  //  app.sendData([0]);
})

function BaseTurnLeft() {
    console.log("BaseTurnLeft called");
    app.sendData([1]);
}
function BaseTurnRight() {
    console.log("BaseTurnRight called");
    app.sendData([2]);
}
function BaseForward() {
    console.log("BaseForward called");
    app.sendData([3]);    
}
function BaseBackward(){
    console.log("BaseBackward called");
    app.sendData([4]);
}
function ShoulderUp() {
    console.log("ShoulderUp called");
    app.sendData([5]);
}
function ShoulderDown() {
    console.log("ShoulderDown called");
    app.sendData([6]);
}
function ElbowFoward() {
    console.log("ElbowForward called");
    app.sendData([7]);
}
function ElbowBackward() {
    console.log("ElbowBackward called");
    app.sendData([8]);
}
function WristTurnLeft() {
    console.log("WristTurnLeft called");
    app.sendData([9]);
}
function WristTurnRight() {
    console.log("WristTurnRight called");
    app.sendData([10]);
}
function Grip() {
    console.log("Grip called");
    app.sendData([11]);
}
function Release() {
    console.log("Release called");
    app.sendData([12]);
}

function pressStart() {
    app.connect();
    document.getElementById("startView").style.display="none";
    document.getElementById("controlsView").style.display="";
  
}
