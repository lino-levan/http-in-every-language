const http = require("http");

const host = '127.0.0.1';
const port = 8080;

const requestListener = (req, res) => {
  res.writeHead(200);
  res.end(`Hello world! The time is ${new Date().toTimeString()} and you requested the path ${req.url}`);
};

const server = http.createServer(requestListener);
server.listen(port, host, () => {
  console.log(`Listening on http://${host}:${port}`);
});