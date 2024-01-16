var mqtt = require('mqtt')

var options = {
    host: '73d972e132fd49e8a46eda35bc71821a.s1.eu.hivemq.cloud',
    port: 8883,
    protocol: 'mqtts',
    username: 'hivemq_test',
    password: 'Idunknow1'
}

// initialize the MQTT client
var client = mqtt.connect(options);

// setup the callbacks
client.on('connect', function () {
    console.log('Connected');
});

client.on('error', function (error) {
    console.log(error);
});

client.on('message', function (topic, message) {
    // called each time a message is received
    console.log('Received message:', topic, message.toString());
   //Lưu trữ vào MySQL
   INSERT_SENSOR_DATA(topic,  message.toString());
});

// subscribe to topic 'my/test/topic'
client.subscribe('test');

// publish message 'Hello' to topic 'my/test/topic'
//client.publish('my/test/topic', 'Hello');

//DATABASE SECTION

// var dateTime = require('node-datetime');
var mysql = require('mysql');
 
//Định nghĩa tham số CSDL
var db_config = {
    host: "localhost",
    user: "root",
    password: "",
    database: "database"
}
 
//Tạo kết nối và xử lý kết nối lại nếu bị mất kết nối đến CSDL
var sql_con;
 
function handleMySQLDisconnect() {
    sql_con = mysql.createConnection(db_config);
    
    sql_con.connect(function(err) {
        if (err) {
            console.log('Error when connecting to database:', err);
            setTimeout(handleDisconnect, 2000);
        }
        console.log("Connected to database!");
    });
 
    sql_con.on('error', function(err) {
        console.log('db error', err);
        if(err.code === 'PROTOCOL_CONNECTION_LOST') {
            handleMySQLDisconnect(); 
        } else { 
            throw err; 
        }
    });
}
 
handleMySQLDisconnect(); //Thực thi lần đầu tiên
 
 
//Viết hàm truy vấn INSERT dữ liệu vào CSDL
function INSERT_SENSOR_DATA(topic, message) { //Hàm Insert giá trị cảm biến
    var sql = "INSERT INTO sensor(topic, message) VALUES ('" + topic +"', '" + message + "')";
    
    sql_con.query(sql, function (err, result) {
        if (err) throw err;
        console.log("Insert sensor data successfull!");
    });
}
 