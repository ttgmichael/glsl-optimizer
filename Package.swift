// swift-tools-version:5.2

import PackageDescription

let package = Package(
    name: "glsl-optimizer",
    products: [
        .library(name: "glslopt", type: .static, targets: ["Header"]),
    ],
    dependencies: [],
    targets: [
        .target(
            name: "Header",
            path: "./",
            exclude: [
                "./contrib",
                "./include",
                "./tests",
                "./projects",
            ],
            sources: [
                "./src/swift",
            ],
            publicHeadersPath: "./src"
        )
    ],
    cxxLanguageStandard: .cxx11
)
