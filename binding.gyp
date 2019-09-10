{
  "targets": [
    {
      "target_name": "node-ctp",
      "sources": [
        "./src/addon.cc", "./src/mdspi.cpp", "./src/wraper_md.cpp",
       ],
      "conditions": [
        [
          "OS=='win'", {
            'variables' : {
              #'import_dir': 'D:/kelly_v2/import',
            },
            "defines": [
              "_HAS_EXCEPTIONS=1"
            ],
            'configurations': {
              'Debug': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    "ExceptionHandling": 1,
                    'RuntimeLibrary': '3' # /MDd
                  },
                },
              },
              'Release': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    "ExceptionHandling": 1,
                    'RuntimeLibrary': '2' # /MD
                  },
                },
              },
            },
            "include_dirs": [
              "./libs/traderapi/6.3.15_20190220_tradeapi64_se_windows"
              "./src",
            ],
            "libraries": [
              "-lthostmduserapi_se.lib"

            ],
            "library_dirs": [
              "./libs/traderapi/6.3.15_20190220_tradeapi64_se_windows"
            ]
          }
        ],
        [
          "OS=='linux'", {
            'variables' : {
            },
            "include_dirs": [
              "./libs/traderapi/v6.3.15_20190220_api_tradeapi_se_linux64",
              "./src",
            ],
            "libraries": [
              "-lthostmduserapi_se"
            ],
            "library_dirs": [
             "./libs/traderapi/v6.3.15_20190220_api_tradeapi_se_linux64"
            ]
          }
        ]
      ],
    }
  ]
}
