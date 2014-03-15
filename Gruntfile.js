'use strict';

module.exports = function(grunt) {
  var forbiddenFn = [
      'var_dump'
    , 'print_r'
    , 'die'
    , 'debug'
    , 'dpm'
    , 'krumo'
    , 'dpr'
    , 'dsm'
    , 'dd'
    , 'ddebug_backtrace'
    , 'dpq'
    , 'dprint_r'
    , 'drupal_debug'
    , 'dvm'
    , 'dvr'
    , 'kpr'
    , 'kprint_r'
    , 'kdevel_print_object'
  ];

  grunt.initConfig({
    jshint: {
      options: {
        jshintrc: 'js/.jshintrc'
      },
      all: {
        src: ['js/{,*/}*.js']
      },
      node: {
        options: { node: true },
        src: ['*.js', '*.json']
      }
    },
    autoprefixer: {
      options: {
        browsers: ['last 2 version', 'ie 8', 'ie 9']
      },
      all: {
        expand: true,
        cwd: 'css/',
        src: '{,*/}*.css',
        dest: 'css/'
      }
    },
    compass: {
      options: {
        cssDir: 'css',
        sassDir: 'sass',
        imagesDir: 'images',
        javascriptsDir: 'js',
        fontsDir: 'fonts',
        relativeAssets: true
      },
      dist: {
        options: {
          outputStyle: 'compressed',
          noLineComments: true,
          debugInfo: false,
          force: true
        }
      },
      server: {
        options: {
          debugInfo: false
        }
      }
    },
    imagemin: {
      dist: {
        options: {
          optimizationLevel: 3,
          progressive: true
        },
        files: [{
          expand: true,
          cwd: 'images',
          src: '{,*/}*.{png,jpg,jpeg}',
          dest: 'images'
        }]
      }
    },
    watch: {
      sass: {
        files: ['sass/**/*.{sass,scss}'],
        tasks: ['compass:server', 'autoprefixer']
      }
    },
    phplint: {
      all: ['{,inc/}*.{php,module,inc,install,theme}']
    },
    "regex-check": {
      all: ['{,inc/}*.{php,module,inc,install,theme}'],
      options: {
        excluded: [],
        pattern: new RegExp('\\b(' + forbiddenFn.join('|') + ')\\s*\\([^)]*\\)', 'g')
      }
    }
  });

  Object.keys(require('./package.json').devDependencies).forEach(function(dep) {
    if (dep.substring(0,6) === 'grunt-' && dep !== 'grunt-cli') grunt.loadNpmTasks(dep);
  });
  grunt.registerTask('lint', ['jshint', 'phplint', 'regex-check']);
  grunt.registerTask('build', ['compass:dist', 'autoprefixer']);
  grunt.registerTask('default', ['lint']);
};
