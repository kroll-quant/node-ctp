{
  "targets": [
    {
      "target_name": "nodeCtp",
      "sources": [
        "./src/nodeCtp.cc",
        "./src/stdbool.h",
        "./src/mdspi.cpp",
        "./src/wrapper_md.cpp",
       ],
      "conditions": [
        [
          "OS=='win'", {
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
              "<(module_root_dir)/libs/traderapi/6.3.15_20190220_tradeapi64_se_windows",
              "<(module_root_dir)/src"
            ],
            "libraries": [
              "-lthostmduserapi_se.lib"
            ],
            "library_dirs": [
              "<(module_root_dir)/libs/traderapi/6.3.15_20190220_tradeapi64_se_windows"
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
