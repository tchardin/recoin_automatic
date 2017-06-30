const port = process.env.PORT || 3000
const express = require('express')

const server = express()
server.use(express.static('public'))
server.use('/web3', express.static(__dirname + '/node_modules/web3/dist'))
server.use('/socket', express.static(__dirname + '/node_modules/socket.io-client/dist'))

server.listen(port, () => {
  console.log(`Server listening to port ${port}`)
})
