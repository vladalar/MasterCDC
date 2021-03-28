var faker = require('faker')

function generateVehicles () {
  var vehicles = []
  for (var id = 0; id < 50; id++) {
    var manufacturer = faker.vehicle.manufacturer()
    var model = faker.vehicle.model()
    var type = faker.vehicle.type()
    var fuel = faker.vehicle.fuel()
    vehicles.push({
      "id": id,
      "manufacturer": manufacturer,
      "model": model,
      "type": type,
      "fuel": fuel,
    })
  }
  return { "vehicles": vehicles }
}
module.exports = generateVehicles