# .PHONY: help build test
# CC = gcc
# help:
# # http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
# 	@grep -E '^[a-zA-Z0-9_%/-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

# build:
# build: ## Build executables
# 	$(MAKE) -C src

# test:
# test: ## Test rbtree implementation
# 	$(MAKE) -C test test
	
# clean:
# clean: ## Clear build environment
# 	$(MAKE) -C src clean
# 	$(MAKE) -C test clean
.PHONY: help build test clean

CC = gcc

help:  ## Show help message
	@grep -E '^[a-zA-Z0-9_%/-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | \
	awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'

build: ## Build executables
	$(MAKE) -C src

test: ## Test rbtree implementation
	$(MAKE) -C test test

clean: ## Clear build environment
	$(MAKE) -C src clean
	$(MAKE) -C test clean

