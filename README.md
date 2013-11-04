# This example demonstrates how to inject a shared library into another process

On it's own, with its little test case, it is running fine. 
It uses the [mach_inject](https://github.com/rentzsch/mach_inject) code 
by Jonathan 'Wolf' Rentzsch.

## The Dock doesn't like it though

I wrote this actually to inject code into the Dock process. It didn't work out. 
You can try it yourself.

A prerequisite for running is to find out the pid of the Dock by running and
setting the only argument of the tool. (As soon as the Dock crashes you have to
do it again.)

<pre>echo "Dock's pid is "`ps -ax | egrep 'Dock.app/Contents/MacOS/Dock' | egrep -v 'egrep' | awk '{ print $1 }'`</pre>

then you go to the target directory and issue:

<pre>sudo DYLD_FALLBACK_LIBRARY_PATH=`pwd` ./mulle-inject-code 12345 # replace with actual pid</pre>

### Failure #1

Often will fail with

`mach_inject failing.. (ipc/send) invalid memory`

this happens. I believe, on 

<pre>err = vm_write( remoteTask, remoteCode, (pointer_t) image, imageSize );</pre>


### Failure #2

If it works, the Dock will crash.

