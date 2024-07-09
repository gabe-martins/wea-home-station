const Data = require('../models/Data');
const moment = require('moment');


module.exports = {
  async store(req, res) {
    let {
      temperature,
      humidity,
      date_time
    } = req.body;

    temperature = temperature !== undefined ? temperature : 999;
    humidity = humidity !== undefined ? humidity : 999;
    date_time = date_time !== undefined ? date_time : moment().format('YYYY-MM-DD HH:mm:ss');

    data = await Data.create({
      temperature,
      humidity,
      date_time
    })

    return res.json(data);
  },

  async index(req, res) {
    try {
      const dados = await Data.find().sort({ createdAt: -1 }).limit(120);
      res.status(200).json(dados);
    } catch (err) {
      res.status(500).json({ message: err.message });
    }
  }
}