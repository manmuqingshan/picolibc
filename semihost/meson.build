#
# SPDX-License-Identifier: BSD-3-Clause
#
# Copyright © 2019 Keith Packard
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#

has_arm_semihost = false

src_semihost = []

machine_dir = 'machine' / host_cpu_family
if fs.is_dir(machine_dir)
  subdir(machine_dir)
endif

# If host_cpu_family supports ARM-style semihosting, the meson.build
# will add the support files to src_semihost.  Check to see if that
# happened and add the rest of the needed files

if src_semihost != []
  src_semihost += files([
    'close.c',
    'exit.c',
    'fstat.c',
    'getentropy.c',
    'gettimeofday.c',
    'isatty.c',
    'kill.c',
    'lseek.c',
    'lseek64.c',
    'mapstdio.c',
    'open.c',
    'read.c',
    'sysconf.c',
    'times.c',
    'unlink.c',
    'write.c',
    'sys_clock.c',
    'sys_close.c',
    'sys_elapsed.c',
    'sys_errno.c',
    'sys_exit.c',
    'sys_exit_extended.c',
    'sys_feature.c',
    'sys_flen.c',
    'sys_get_cmdline.c',
    'sys_getc.c',
    'sys_heapinfo.c',
    'sys_iserror.c',
    'sys_istty.c',
    'sys_open.c',
    'sys_putc.c',
    'sys_read.c',
    'sys_remove.c',
    'sys_rename.c',
    'sys_seek.c',
    'sys_system.c',
    'sys_tickfreq.c',
    'sys_time.c',
    'sys_tmpnam.c',
    'sys_write.c',
    'sys_write0.c',
  ])

  if tinystdio
    src_semihost += 'iob.c'
  endif

  inc_headers = ['semihost.h']
  if really_install
    install_headers(inc_headers,
                    install_dir: include_dir)
  endif

  inc = [inc, include_directories('.')]
  inc_args += '-I' + meson.current_source_dir()

  has_semihost = true

  has_arm_semihost = true

  has_semihost_args = true

  foreach params : targets
    target = params['name']
    target_dir = params['dir']
    target_c_args = params['c_args']
    target_lib_prefix = params['lib_prefix']

    instdir = join_paths(lib_dir, target_dir)

    libsemihost_name = 'semihost'

    set_variable('lib_semihost' + target,
		 static_library(join_paths(target_dir, target_lib_prefix + libsemihost_name),
				src_semihost,
				install : really_install,
				install_dir : instdir,
				include_directories : inc,
				c_args : target_c_args + c_args))
    
  endforeach

  if enable_cdefs_tests
    ignore_headers = []
    foreach header : inc_headers

      if not (header in ignore_headers) and not (header.startswith('_'))
        test_name = 'check-cdef-' + header

        test(test_name,
             validate_cdefs,
             args: [meson.current_source_dir() / header] + cc.cmd_array() + c_args + inc_args,
             suite: 'headers')
      endif
    endforeach
  endif

endif

if not has_semihost and get_option('fake-semihost')
  subdir('fake')
endif

