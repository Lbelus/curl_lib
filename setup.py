from setuptools import setup, Extension
import os

# Function to collect all .c files from the src directory and its subdirectories
def collect_source_files(directory):
    source_files = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):
                source_files.append(os.path.join(root, file))
    return source_files

sources_files = collect_source_files('./src/')

module = Extension('curl_api_module',
                   sources=sources_files,
                   include_dirs=['./include/'],  
                   libraries=['ssl', 'crypto'],  # Linking against OpenSSL libraries
                   library_dirs=['/usr/lib', '/usr/local/lib'],
                   extra_compile_args=['-g', '-O0', '-fsanitize=address,undefined'],
                   extra_link_args=['-fsanitize=address,undefined'])

setup(name='CurlApiModule',
      version='1.1',
      description='Python interface for curl api',
      ext_modules=[module])