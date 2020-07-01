namespace Sourdoh.Api.Models
{
    public class SourdohDatabaseSettings : ISourdohDatabaseSettings
    {
        public string SourdohCollectionName { get; set; }
        public string ConnectionString { get; set; }
        public string DatabaseName { get; set; }
    }

    public interface ISourdohDatabaseSettings
    {
        string SourdohCollectionName { get; set; }
        string ConnectionString { get; set; }
        string DatabaseName { get; set; }
    }
}
