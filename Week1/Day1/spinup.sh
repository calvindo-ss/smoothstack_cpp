# Spins up a Docker container

# sets image name
export docker_img="dockerdev"

# mounts current working directory to /source_directory
docker run -dit -v "$(pwd)":/source_directory $docker_img bash