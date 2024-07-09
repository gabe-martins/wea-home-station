const { Router } = require("express");
const DataController = require('./controllers/DataController');

const routes = Router();

// Rotas do CRUD
routes.post('/store_data', DataController.store);
routes.get('/get_data', DataController.index);

module.exports = routes;