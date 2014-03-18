{
  'variables': {
    'guidolib%': 'lib/guido-engine',
  },
  'conditions': [
    ['OS=="linux"', {
      'variables': {
        'guidolib_out%': '<(guidolib)/cmake',
      }
    }],
  ],
  'targets': [
    {
      'target_name': 'standbyme',
      'dependencies': [],
      'variables': {
        
      },
      'cflags': [
        
      ],
      'defines': [
      
      ],
      'include_dirs': [
        "<!(node -p -e \"require('path').relative('.', require('path').dirname(require.resolve('nan')))\")",
        '<(guidolib)',
        '<(guidolib)/src/lib',
        '<(guidolib)/src/graphic',
        '<(guidolib)/src/abstract',
        '<(guidolib)/src/parser',
        '<(guidolib)/src/tools',
        '<(guidolib)/src/misc',
        '<(guidolib)/src/include',
        '<(guidolib)/src/devices',
        '<(guidolib)/src/maps',
      ],
      'link_settings': {
        'ldflags': [
        ],
        'conditions': [
          ['OS=="linux"', {
            'libraries': [
              '../<(guidolib_out)/libGUIDOEngine.so.1',
              '../<(guidolib_out)/libGUIDOEngine.so.1.50',
            ],
            'cflags': [
              '-std=c++0x',
            ],
          }],
        ],
        'libraries': [
        ]
      },
      'sources': [
        'src/binding.cc',
        'src/musicxml_parser.cc'
      ]
    }
  ]
}
