# Spins up a Docker container

# sets image name
export docker_img="dockerdev"

# mounts local current working directory to /home/calvin/source_directory in the container
docker run -dit -e COLORTERM=truecolor -v "$(pwd)":/home/calvin/source_directory:z -u $(whoami) $docker_img bash
