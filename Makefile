project_name = ssr-perf-server-reason-react

DUNE = opam exec -- dune
opam_file = $(project_name).opam

.PHONY: help
help: ## Print this help message
	@echo "";
	@echo "List of available make commands";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: clean
clean: ## Clean artifacts
	$(DUNE) clean

.PHONY: dev
dev: ## Build in watch mode
	$(DUNE) build -w --profile=dev @all

.PHONY: build
build: ## Build the project, including non installable libraries and executables
	$(DUNE) build --profile=dev

.PHONY: build-prod
build-prod: ## Build for production (--profile=prod)
	$(DUNE) build --profile=prod

.PHONY: create-switch
create-switch: ## Create opam switch
	opam switch create . 5.1.1 --deps-only --with-test -y

.PHONY: install
install:
	opam install . --deps-only --with-test --with-doc --with-dev-setup
	cd demo && npm install

.PHONY: pin
pin: ## Pin dependencies
	opam pin add server-reason-react.dev "https://github.com/ml-in-barcelona/server-reason-react.git#fb6836045f4ee56cf42c409f2830674146e0eea4" -y
	opam pin add simple_httpd.dev "https://github.com/craff/simple_httpd.git#c72fce03df902f72f77f82b9c70c1674982f52b2" -y

.PHONY: init
init: create-switch pin install ## Create a local dev enviroment

.PHONY: serve
serve: build ## Serve the demo executable
	dune exec _build/default/src/server.exe
