#
# SPDX-License-Identifier: BSD-3-Clause
#
# Copyright © 2021 Keith Packard
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

lib_semihost_srcs = [
  'e9_exit.c',
  'e9_kill.c',
  'e9_stub.c',
  ]

if tinystdio
  lib_semihost_srcs += 'e9_io.c'
endif

has_semihost = true

objcopy = find_program('objcopy', required: false)

foreach params : targets
  target = params['name']
  target_dir = params['dir']
  target_c_args = params['c_args']
  target_lib_prefix = params['lib_prefix']

  instdir = join_paths(lib_dir, target_dir)

  libsemihost_name = 'semihost'

  local_lib_semihost_target = static_library(join_paths(target_dir, target_lib_prefix + libsemihost_name),
				       lib_semihost_srcs,
				       install : really_install,
				       install_dir : instdir,
				       include_directories : inc,
				       c_args : target_c_args + c_args,
				       pic: false)

  set_variable('lib_semihost' + target, local_lib_semihost_target)

endforeach

if objcopy.found()
  # Stub BIOS which provides a jump instruction at the CPU start
  # address (0xfffffff0) to get us to our default start address at 1MB
  # (0x100000)

  bios_ld = '@0@/@1@'.format(meson.current_source_dir(), 'bios.ld')
  link_args = ['-nostdlib', '-m32', '-Wl,--build-id=none', '-T', bios_ld]
  # x86_64 compiler needs a elf32-i386 target set if using -m32.
  if compiler_id == 'gcc' and target_machine.cpu_family() == 'x86_64'
    link_args = ['-Wl,-b,elf32-i386', '-Wl,-melf_i386'] + link_args
  endif

  bios = executable('bios', 'bios.S',
		    c_args: ['-m32'] + c_args,
                    include_directories: inc,
                    link_depends: [bios_ld],
		    link_args: link_args)

  bios_bin = custom_target('bios.bin',
		           build_by_default: true,
		           input: bios,
		           install: really_install,
		           install_dir: instdir,
		           output: 'bios.bin',
		           command: [objcopy, '-O', 'binary', '--only-section=.text', '@INPUT@', '@OUTPUT@'])
endif

