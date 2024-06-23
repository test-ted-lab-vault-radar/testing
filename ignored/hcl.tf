terraform {
  required_providers {
    null = {
      source = "hashicorp/null"
      version = "~> 3.0"
    }
  }
}

provider "null" {}

resource "null_resource" "ssh_to_server" {
  provisioner "local-exec" {
    command = <<EOT
      sshpass -p "${var.password}" ssh ${var.username}@192.168.10.1 "cat /var/log/messages"
    EOT
  }
  triggers = {
    always_run = timestamp()
  }
}

variable "username" {
  type    = string
  default = "admin"
}

variable "password" {
  type    = string
  default = "password"
}
