# A sample Guardfile
# More info at https://github.com/guard/guard#readme

# Add files and commands to this file, like the example:
#   watch(%r{file/path}) { `command(s)` }
#
guard 'shell' do
    watch(%r{samples/.+\.bl$}) do |m|
        `pkill blocky`
        `./blocky #{m[0]} &`
    end
end
