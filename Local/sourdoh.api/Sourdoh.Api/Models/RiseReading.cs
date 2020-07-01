using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;
using System;

namespace Sourdoh.Api.Models
{
    public class RiseReading
    {
        [BsonId]
        [BsonRepresentation(BsonType.ObjectId)]
        public string Id { get; set; }

        public DateTime Reading { get; set; }

        public decimal TemperatureCelcius { get; set; }

        public decimal HumidityPercent { get; set; }

        public int Distance { get; set; }

    }
}