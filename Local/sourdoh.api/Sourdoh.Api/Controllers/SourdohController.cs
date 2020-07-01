using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Sourdoh.Api.Models;
using Sourdoh.Api.Services;
using System;

namespace Sourdoh.Api.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class SourdohController : ControllerBase
    {
        private readonly ILogger<SourdohController> _logger;
        private readonly SourdohService _sourdohService;

        public SourdohController(ILogger<SourdohController> logger, SourdohService sourdohService)
        {
            _logger = logger;
            _sourdohService = sourdohService;
        }

        [HttpGet]
        public dynamic Get()
        {
            return _sourdohService.Get();
        }

        [HttpPost]
        [Consumes("application/x-www-form-urlencoded")]
        public void Add([FromForm] RiseReading riseReading)
        {
            if (riseReading != null)
            {
                riseReading.Reading = DateTime.Now;
                _sourdohService.Create(riseReading);
            }
        }
    }
}
