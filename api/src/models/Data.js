const mongoose = require('mongoose');

const DataSchema = new mongoose.Schema({
  temperature: Number, 
  humidity: Number,
  date_time: String
},{
  timestamps: true,
})

module.exports = mongoose.model("Data", DataSchema);