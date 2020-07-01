using MongoDB.Driver;
using Sourdoh.Api.Models;
using System.Collections.Generic;
using System.Linq;

namespace Sourdoh.Api.Services
{

    public class SourdohService
    {
        private readonly IMongoCollection<RiseReading> _rr;

        public SourdohService(ISourdohDatabaseSettings settings)
        {
            var client = new MongoClient(settings.ConnectionString);
            var database = client.GetDatabase(settings.DatabaseName);

            _rr = database.GetCollection<RiseReading>(settings.SourdohCollectionName);
        }

        public List<RiseReading> Get() =>
            _rr.Find(rr => true).ToList();

        public RiseReading Get(string id) =>
            _rr.Find<RiseReading>(rr => rr.Id == id).FirstOrDefault();

        public RiseReading Create(RiseReading book)
        {
            _rr.InsertOne(book);
            return book;
        }

        public void Update(string id, RiseReading rrIn)
        {
            _rr.ReplaceOne(rr => rr.Id == id, rrIn);
        }

        public void Remove(RiseReading rrIn) =>
            _rr.DeleteOne(rr => rr.Id == rrIn.Id);

        public void Remove(string id) =>
            _rr.DeleteOne(rr => rr.Id == id);
    }
}
